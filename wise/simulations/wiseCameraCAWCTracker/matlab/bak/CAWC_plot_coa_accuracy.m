% function []=CAWC_plot_coa_resUsage()
% This script reads the data generated by the app 'wiseCameraCAWCTracker'
% and computes the following statistics:
%   - Visualization of the error for each camera/run as an independent plot
%   - Average tracking error on the image-plane and ground-plane (camera tracker)
%   - Average tracking error on the image-plane and ground-plane (coalition tracker)
%
%
%   Author:      Juan Carlos SanMiguel (juancarlos.sanmiguel@uam.es)
%   Affiliation: University Autonoma of Madrid
%   URL:         http://www-vpu.ii.uam.es/~jcs
%   Date:        September 2015
clc; clear all; close all;
addpath('./utils');

%% SETTINGS
SHOW_DATA = 0; %=0(none) =1(shows results for video frames) =2(shows overall results for sequence/run)

%% LOAD & PREPROCESS DATA 
% delete the files in './data' to reload all data
root_dir = '/home/jcs/code/svn/multicamera/wise-mnet/dev/wise/simulations/wiseCameraCAWCTracker/';
experiment_dir = 'res_P_t09_7fps_25s_r50_f1';

if exist(['./data/' experiment_dir '.mat'], 'file') == 2
    load(['./data/' experiment_dir '.mat']);
else    
    [runs,coa]=load_coa_data([root_dir experiment_dir]); %coalition tracking data
    [cams.track,ids,cids]=load_cams_data([root_dir experiment_dir]); %camera tracking data
    [cams.usage,ids,cids]=load_cams_consumption([root_dir experiment_dir]);%camera consumption
    [Ncams,Nruns,PROclk,SENclk,speedF,FPSreq,FPSrea,evalFrames] = preprocess_data(cams);
    save(['./data/' experiment_dir '.mat']);
end

%% PLOT SENSING-VS-PROCESSING FOR COALITION CAMERAS
en.SENact = zeros(numel(PROclk), numel(FPSreq)); en.SENact_c = zeros(numel(PROclk), numel(FPSreq));
en.SENidl = zeros(numel(PROclk), numel(FPSreq)); en.SENidl_c = zeros(numel(PROclk), numel(FPSreq));
en.PROact = zeros(numel(PROclk), numel(FPSreq)); en.PROact_c = zeros(numel(PROclk), numel(FPSreq));
en.PROidl = zeros(numel(PROclk), numel(FPSreq)); en.PROidl_c = zeros(numel(PROclk), numel(FPSreq));
en.COMact = zeros(numel(PROclk), numel(FPSreq)); en.COMact_c = zeros(numel(PROclk), numel(FPSreq));
en.COMidl = zeros(numel(PROclk), numel(FPSreq)); en.COMidl_c = zeros(numel(PROclk), numel(FPSreq));
en.steps = zeros(numel(PROclk), numel(FPSreq)); en.time = zeros(numel(PROclk), numel(FPSreq));

en.SENtot = zeros(numel(PROclk), numel(FPSreq)); en.SENtot_c = zeros(numel(PROclk), numel(FPSreq));
en.PROtot = zeros(numel(PROclk), numel(FPSreq)); en.PROtot_c = zeros(numel(PROclk), numel(FPSreq));
en.COMtot = zeros(numel(PROclk), numel(FPSreq)); en.COMtot_c = zeros(numel(PROclk), numel(FPSreq));
en.COMtot_bits = zeros(numel(PROclk), numel(FPSreq)); en.COMtot_bits_c = zeros(numel(PROclk), numel(FPSreq));

%% COMPUTE TRACKING ERROR FOR CAMERAS
scenario = 'pets2009'; configuration;
config.mpp = config.mpp/4;
% scenario = 'ICGLab6_chap'; configuration;

%read camera model
for c=1:Ncams
    ind = find(cams.usage{c,1}.camID == config.selCams);
    fprintf('Loading %s\n',config.calFile{ind});    
    cams.calib(c) = cameraModel([config.datasetDir config.calFile{ind}], config);
end

%read image plane annotation (feet location in format <FR,XPOS,YPOS>)
ind = find(cams.track{1,1}.targetID == config.nTargetIDs);
tgtGT_gp = dlmread([config.datasetDir config.gtFile{ind}], ',');

%read image plane annotation (bounding box in format <CAM,FR,XPOS,YPOS,WIDTH,HEIGHT>)
%tgtIni_ip = dlmread([config.datasetDir config.gtFileInit{1}], ',');

%compute Image-plane (IP) and Ground-Plane (GP) error for cameras
err.CAMGP = cell(Ncams,numel(PROclk), numel(FPSreq));  %err.CAMGP_c = zeros(Ncams,numel(PROclk), numel(SENfps_req));
err.CAMIP = cell(Ncams,numel(PROclk), numel(FPSreq));  %err.CAMIP_c = zeros(Ncams,numel(PROclk), numel(SENfps_req));
for c=1:Ncams        
    for r=1:Nruns
        
        %video file of camera
        if SHOW_DATA == 1
            ind = find(cams.usage{c,1}.camID == config.selCams);
            v = VideoReader([config.datasetDir config.vidFile{ind}]);
        end
        
        if SHOW_DATA
            figure('Name', sprintf('camera %d - run %d - %.2fGhz - %.2ffps',c,r,cams.usage{c,r}.PRO.clockfreq/1e9,cams.usage{c,r}.SEN.FPSrea), 'units','normalized','outerposition',[0 0 1 1]);
        end
        
        %resizing factor of input images
        xf = 1/cams.track{c,r}.sCols;
        yf = 1/cams.track{c,r}.sRows;
        
        trk_cam(c,r).start = -1;
        trk_cam(c,r).end = -1;
        frRead = 0;
        
        for n=1:numel(cams.track{c,r}.X0w); %total number of steps
            
            trk_cam(c,r).xy_gp(n) = {[cams.track{c,r}.X0w(n) cams.track{c,r}.Y0w(n)]}; %ground-plane estimation
            trk_cam(c,r).xy_ip(n) = {[cams.track{c,r}.X0i(n) cams.track{c,r}.Y0i(n)]}; %image-plane estimation
            
            ind=find(tgtGT_gp(:,1) == cams.track{c,r}.frID(n)); %find current frame in ground-truth
            if (cams.track{c,r}.X0i(n) > 0 && numel(ind)>0) %if such frame exists
                
                %convert ground-truth to image-plane and compute errors in GP and IP
                tmp_m=[];
                [tmp_m(1),tmp_m(2)]=cams.calib(c).worldToImage(tgtGT_gp(ind,2),tgtGT_gp(ind,3),0);
                tmp_m = tmp_m./[xf yf];
                trk_cam(c,r).errIP(n)=norm(tmp_m - trk_cam(c,r).xy_ip{n});
                
                error_gp = config.mpp.*(tgtGT_gp(ind,2:3) - trk_cam(c,r).xy_gp{n});
                trk_cam(c,r).errGP(n)=norm(error_gp);
                
                %update start and end frames for the target data
                if (trk_cam(c,r).start == -1)
                    trk_cam(c,r).start = cams.track{c,r}.frID(n)+1;
                end
                trk_cam(c,r).end = cams.track{c,r}.frID(n)+1;
                
            else %if such frame does not exist
                
                tmp_m = [NaN NaN];
                trk_cam(c,r).errGP(n)=-1;
                trk_cam(c,r).errIP(n)=-1;
            end
            
            if SHOW_DATA==1
                %read corresponding video frame
                frame = readFrame(v);frRead = frRead + 1;
                while (frRead ~= cams.track{c,r}.frID(n)+1)
                    frame = readFrame(v);frRead = frRead + 1;
                end
                frame = imresize(frame, [480 752]);
                
                %plot tracking data (image, IP error & utility)
                subplot(4,1,1:2); imshow(frame); hold on;
                plot(tmp_m(1),tmp_m(2),'g+','MarkerSize',12,'LineWidth',3);
                plot(trk_cam(c,r).xy_ip{n}(1),trk_cam(c,r).xy_ip{n}(2),'b+','MarkerSize',12,'LineWidth',3);
                text('units','pixels','position',[10 10],'fontsize',16,'color','red', 'string',sprintf('Cam%d - run=%d Fr=%d u=%.2f',c,r,cams.track{c,r}.frID(n),cams.track{c,r}.u(n)));
                if cams.track{c,r}.Xi(n) > 0
                    rectangle('Position', [cams.track{c,r}.Xi(n) cams.track{c,r}.Yi(n) cams.track{c,r}.Wi(n) cams.track{c,r}.Hi(n)],'EdgeColor','blue');
                end
                hold off;
                %subplot 513; plot( cams.track{c,r}.frID(1:n),trk_cam(c,r).errIP); ylabel('IP error (pixels)');
                subplot 413; plot( cams.track{c,r}.frID(1:n),trk_cam(c,r).errGP); ylabel('GP error (m)'); axis([1 cams.track{c,r}.frID(n)+1 min(min(trk_cam(c,r).errGP),0) min(8,max(trk_cam(c,r).errGP))+0.1]) 
                subplot 414; plot( cams.track{c,r}.frID(1:n),cams.track{c,r}.u(1:n)); ylabel('utility'); axis([1 cams.track{c,r}.frID(n)+1 min(0,min(cams.track{c,r}.u(1:n))) max(1,max(cams.track{c,r}.u(1:n)))]) 
            end
        end
        
        if SHOW_DATA==2
            subplot 411;
            scatter(trk_cam(c,r).errIP,cams.track{c,r}.u(1:n)); xlabel('IP error'); ylabel('utility');
            ind1 = find(trk_cam(c,r).errIP < 50);
            ind2 = find(trk_cam(c,r).errIP > 50);
            a=cams.track{c,r}.u(1:n);
            title(sprintf('Camera %d - run %d - right (%.2f-%.2f) - wrong (%.2f-%.2f)',c,r,mean(a(ind1)),var(a(ind1)),mean(a(ind2)),var(a(ind2))));
            
            subplot 412; plot( cams.track{c,r}.frID(1:n),trk_cam(c,r).errIP); ylabel('IP error'); %axis([cams.track{c,r}.frID(1) cams.track{c,r}.frID(end) 0 200]);
            subplot 413; plot( cams.track{c,r}.frID(1:n),trk_cam(c,r).errGP); ylabel('GP error');
            subplot 414; plot( cams.track{c,r}.frID(1:n),cams.track{c,r}.u(1:n)); ylabel('utility');
           
        end
        
        if SHOW_DATA>0
           pause;
        end
        
        %store results
        ip = find(PROclk==cams.usage{c,r}.PRO.clockfreq);
        is = find(FPSreq==cams.usage{c,r}.SEN.FPSreq);
        
        %frames where data is accumulated        
        a = cams.track{c,r}.frID;
        b = evalFrames;
        ind = find(ismember(a, b)); % Extract the elements of a at those indexes.
        if numel(ind) ~= numel(evalFrames)
            %we uniformly sample the results if we do not find the frames to compare
            ind = find(trk_cam(c,r).errGP > 0);
            if isempty(ind)
                ind=1:size(trk_cam(c,r).errGP,2);
            else
                x = round(linspace(1,numel(ind),numel(evalFrames)));
                ind= ind(x);
            end
        end
        numel(ind)
        
        %compute the mean error at sequence level
        err.CAMGP(c,ip,is) = {[err.CAMGP{c,ip,is} mean(trk_cam(c,r).errGP(ind))]}; %ground-plane error
        err.CAMIP(c,ip,is) = {[err.CAMIP{c,ip,is} mean(trk_cam(c,r).errIP(ind))]}; %image-plane error
    end
    close all;
end

%mean error across all runs
for c=1:size(err.CAMGP,1)
    for ip=1:size(err.CAMGP,2)
        for is=1:size(err.CAMGP,3)
            err.CAMGPm(c,ip,is) = mean(err.CAMGP{c,ip,is}(:));
            err.CAMGPv(c,ip,is) = std(err.CAMGP{c,ip,is}(:));
            
            err.CAMIPm(c,ip,is) = mean(err.CAMIP{c,ip,is}(:));
            err.CAMIPv(c,ip,is) = std(err.CAMIP{c,ip,is}(:));
        end
    end
end

%% COMPUTE TRACKING ERROR FOR COALITION
err.COA_GP = cell(numel(PROclk), numel(FPSreq));
err.COA_IP = cell(numel(PROclk), numel(FPSreq));
for tt=1:numel(coa)
    
    r = find (runs == coa(tt).run); %run number
    
    %compute error in the ground-plane for each step
    for n=1:size(coa(tt).res,2);
        trk_coa(tt).xy_gp(n) = {coa(tt).res(n).x{1}(1:2)};
        
        ind=find(tgtGT_gp(:,1) == coa(tt).res(n).frameID+1);%find current frame in ground-truth
        if isempty(ind)
            trk_coa(tt).errGP(n)=NaN;
            trk_coa(tt).errIP(n)=NaN;
        else
            error_gp = config.mpp.*(tgtGT_gp(ind,2:3) - trk_coa(tt).xy_gp{n});
            trk_coa(tt).errGP(n)=norm(error_gp);
            trk_coa(tt).frID(n) = coa(tt).res(n).frameID+1;
            
            errC = [];
            for c=1:Ncams
                [tmp_m(1),tmp_m(2)]=cams.calib(c).worldToImage(tgtGT_gp(ind,2),tgtGT_gp(ind,3),0);
                [tmpC(1),tmpC(2)]=cams.calib(c).worldToImage(trk_coa(tt).xy_gp{n}(1),trk_coa(tt).xy_gp{n}(2),0);
                %sz = cams.track{c,r}.Wi(n)*cams.track{c,r}.Hi(n);
                sz=1;
                errC = [errC norm(tmp_m-tmpC)/sz];
            end
            trk_coa(tt).errIP(n)=min(errC);
        end
    end
    
    %find the effective duration of the coalition
    coa(tt).start = Inf;
    coa(tt).end = -1;
    for c=1:Ncams
        coa(tt).start = min(trk_cam(c,r).start, coa(tt).start);
        coa(tt).end = min(trk_cam(c,r).end, coa(tt).end);
    end
    
    %store results
    ip = find(PROclk== cams.usage{1,r}.PRO.clockfreq);
    is = find(FPSreq==cams.usage{1,r}.SEN.FPSreq);
    
    %compute the mean error at sequence level    
    a = trk_coa(tt).frID;
    b = evalFrames;
    ind = find(ismember(a, b)); % Extract the elements of a at those indexes.
    if numel(ind) ~= numel(evalFrames)
        %we uniformly sample the results if we do not find the frames to compare
        ind = find(trk_coa(tt).errGP > 0);
        if isempty(ind)
            ind=1:size(trk_coa(tt).errGP,2);
        else
            x = round(linspace(1,numel(ind),numel(evalFrames)));
            ind= ind(x);
        end
    end        
    err.COA_GP(ip,is) = {[err.COA_GP{ip,is} mean(trk_coa(tt).errGP(ind))]};%ground-plane error
    err.COA_IP(ip,is) = {[err.COA_IP{ip,is} mean(trk_coa(tt).errIP(ind))]};%image-plane error
end

%mean error across all runs

for ip=1:size(err.COA_IP,1)
    for is=1:size(err.COA_IP,2)
        err.COA_GPm(ip,is) = mean(err.COA_GP{ip,is}(:));
        err.COA_GPv(ip,is) = std(err.COA_GP{ip,is}(:));
        
        err.COA_IPm(ip,is) = mean(err.COA_IP{ip,is}(:));
        err.COA_IPv(ip,is) = std(err.COA_IP{ip,is}(:));
    end
end

%% PLOT ERRORS

if(numel(FPSreq)>2 && numel(PROclk) > 2)
    % 3D plot for simultaneous testing of framerate and processing clock
    [N,M]=meshgrid(FPSreq,PROclk);
    hp=figure('Name','Tracking error ground-plane');
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.CAMGPm(c,:,:),[numel(PROclk) numel(FPSreq)])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error GP (m)',PROclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.COA_GPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',PROclk,FPSreq);
    
    hp=figure('Name','Tracking error image-plane');
    for c=1:Ncams
        subplot(2,4,c); mesh(N,M,reshape(err.CAMIPm(c,:,:),[numel(PROclk) numel(FPSreq)])); plot_labels_axis(sprintf('Camera %d',c),'Mean tracking error IP (pixels)',PROclk,FPSreq);
    end
    subplot(2,4,8); mesh(N,M,err.COA_IPm); plot_labels_axis('Coalition','Mean tracking error GP (m)',PROclk,FPSreq);
    
else
    % 2D bar plot for independent testing of framerate or processing clock
    if numel(FPSreq)>1 %framerate testing
%         fip1=figure('Name',sprintf('Tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         tmp_m = err.CAMIPm; tmp_m(end+1,:,:) = err.COA_IPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
%         tmp_v = err.CAMIPv; tmp_v(end+1,:,:) = err.COA_IPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
%         bar(tmp_m); hold on; legend(strread(num2str(SENfps_req),'%s')');        
%         set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('IP tracking error (pixels)');
%         title(sprintf('Tracking IP error for P=%.2fGHz and different framerates',PROclk(1)/1e9));
        
        fgp1=figure('Name',sprintf('Tracking GP error for P=%.2fGHz',PROclk(1)/1e9),'Position', [100, 100, 700, 300]);
        tmp_m = err.CAMGPm; %tmp_m(end+1,:,:) = err.COA_GPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
        tmp_m=reshape(tmp_m, [Ncams max(size(err.COA_IP))]);
        %tmp_v = err.CAMGPv; tmp_v(end+1,:,:) = err.COA_GPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
        labels=strread(num2str(FPSreq),'%s');
        for ll=1:numel(labels)
            labels{ll} = [labels{ll} ' fps'];
        end
        b=bar(tmp_m); hold on; leg=legend(labels','Orientation','Horizontal','Location','Northoutside');        
        
        labels=strread(num2str(cids),'%s');
        for ll=1:numel(labels)
            labels{ll} = ['Camera ' labels{ll} ];
        end
%         title(sprintf('Tracking GP error for P=%.2fGHz and different framerates',PROclk(1)/1e9));
        %set(gca,'XTick',1:Ncams+1, 'XTickLabel',[labels;{'Coalition'}]); 
        set(gca,'XTick',1:Ncams, 'XTickLabel',labels); 
        ylabel('Average tracking error (m)');%xlabel('camera');
        box off;  
        axis([0.5 numel(cids)+0.5 0 3.25])
%         axis tight;

        
        Xgp=[];Xip=[];
        for is=1:numel(FPSreq)
            Xgp = [Xgp; err.COA_GP{1,is}(:)'];
            Xip = [Xip; err.COA_IP{1,is}(:)'];
        end
        Xgp = Xgp';
        Xip = Xip';
        
%         fip2=figure('Name',sprintf('Coalition tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         T = bplot(Xip,'points'); legend(T,'location','northeast');
%         set(gca,'XTick',1:numel(SENfps_req), 'XTickLabel',SENfps_req);
%         xlabel('Sensing framerate (fps)');   ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image-Plane for P=%.2fGHz',PROclk(1)/1e9));
        
        fgp2=figure('Name',sprintf('Coalition tracking GP error for P=%.2fGHz',PROclk(1)/1e9));
        T = bplot(Xgp,'points'); legend(T,'location','northeast');
        set(gca,'XTick',1:numel(FPSreq), 'XTickLabel',FPSreq);
        xlabel('Sensing framerate (fps)');   ylabel('Coalition tracking error (m)');
        %title(sprintf('Coalition error in Ground-Plane for P=%.2fGHz',PROclk(1)/1e9));
        
%         saveas(fip1, 'figs/TrackErrIP_cmp_sensing.eps','epsc'); saveas(fip1, 'figs/TrackErrIP_cam_sensing.fig');
        saveas(fgp1, 'figs/TrackErrGP_cmp_sensing.eps','epsc'); saveas(fgp1, 'figs/TrackErrGP_cam_sensing.fig');
%         saveas(fip2, 'figs/TrackErrGP_coa_sensing.eps','epsc'); saveas(fip2, 'figs/TrackErrIP_coa_sensing.fig');
        saveas(fgp2, 'figs/TrackErrGP_coa_sensing.eps','epsc'); saveas(fgp2, 'figs/TrackErrGP_coa_sensing.fig');
        
        SEN.Ncams = Ncams;
        SEN.Nruns = Nruns;
        SEN.Xgp = Xgp;
        SEN.Xip = Xip;
        SEN.fps = FPSreq;
        SEN.err.COA_GP = err.COA_GP;
        SEN.err.COA_IP = err.COA_IP;
        SEN.err.CAMGP = err.CAMGP;
        SEN.err.CAMIP = err.CAMIP;       
        SEN.cids = cids;
        SEN.err.CAMGPm = err.CAMGPm;
        SEN.dataDir = dataDir;
        save figs/TrackErrIP_cmp_sensing.mat SEN;
    end
    
    if  numel(PROclk)>1 %processing clock testing
%         fip1=figure('Name',sprintf('Tracking IP error for fps=%.2f',SENfps_req(1)));
%         tmp_m = err.CAMIPm; tmp_m(end+1,:,:) = err.COA_IPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
%         tmp_v = err.CAMIPv; tmp_v(end+1,:,:) = err.COA_IPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
%         bar(tmp_m); hold on; legend(strread(num2str(PROclk/1e9),'%s')');
%         set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('IP tracking error (pixels)');
%         title(sprintf('Tracking IP error for fps=%.2f and different processing clocks',SENfps_req(1)));
        
        fgp1=figure('Name',sprintf('Tracking GP error for fps=%.2f',FPSreq(1)));
        tmp_m = err.CAMGPm; tmp_m(end+1,:,:) = err.COA_GPm; tmp_m=reshape(tmp_m, [Ncams+1 max(size(err.COA_IP))]);
        tmp_v = err.CAMGPv; tmp_v(end+1,:,:) = err.COA_GPv; tmp_v=reshape(tmp_v, [Ncams+1 max(size(err.COA_IP))]);
        labels=strread(num2str(PROclk/1e9),'%s');
        for ll=1:numel(labels)
            labels{ll} = [labels{ll} ' GHz'];
        end
        bar(tmp_m); hold on; legend(labels');
        title(sprintf('Tracking GP error for fps=%.2f and different processing clocks',FPSreq(1)));
        set(gca,'XTick',1:Ncams+1, 'XTickLabel',[strread(num2str(1:Ncams),'%s');{'Coalition'}]); xlabel('camera');ylabel('GP tracking error (m)');
        
        Xgp=[];Xip=[];
        for ip=1:numel(PROclk)
            Xgp = [Xgp; err.COA_GP{ip,1}(:)'];
            Xip = [Xip; err.COA_IP{ip,1}(:)'];
        end
        
        fgp2=figure('Name',sprintf('Coalition tracking GP error for P=%.2fGHz',PROclk(1)/1e9));
        T = bplot(Xgp','points');
        legend(T,'location','northeast');
        set(gca,'XTick',1:numel(PROclk), 'XTickLabel',PROclk/1e9);
         xlabel('Processor clock (Ghz)');   ylabel('Coalition tracking error (m)');
        %title(sprintf('Coalition error in Ground-Plane for P=%.2fGHz',PROclk(1)/1e9));
%         
%         fip2=figure('Name',sprintf('Coalition tracking IP error for P=%.2fGHz',PROclk(1)/1e9));
%         T = bplot(Xip','points');
%         legend(T,'location','northeast');
%         set(gca,'XTick',1:numel(PROclk), 'XTickLabel',PROclk/1e9);
%          xlabel('Processor clock (Ghz)');    ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image-Plane for fps=%.2fGHz',SENfps_req(1)));
%         
%         fip_=figure('Name',sprintf('Coalition Tracking IP error for fps=%.2f',SENfps_req(1)));
%         errorbar(err.COA_IPm,sqrt(err.COA_IPv),'rx','MarkerSize',12 );
%         set(gca,'XTick',1:numel(PROclk), 'XTickLabel',PROclk/1e9);
%         xlabel('Processor clock (Ghz)');   ylabel('Average tracking error (pixels)');
%         title(sprintf('Coalition error in Image Plane for fps=%.2f',SENfps_req(1)));
        
%         saveas(fip1, 'figs/TrackErrIP_cmp_pro.eps','epsc'); saveas(fip1, 'figs/TrackErrIP_cam_pro.fig');
        saveas(fgp1, 'figs/TrackErrGP_cmp_pro.eps','epsc'); saveas(fgp1, 'figs/TrackErrGP_cam_pro.fig');
%         saveas(fip2, 'figs/TrackErrGP_coa_pro.eps','epsc'); saveas(fip2, 'figs/TrackErrIP_coa_pro.fig');
        saveas(fgp2, 'figs/TrackErrGP_coa_pro.eps','epsc'); saveas(fgp2, 'figs/TrackErrGP_coa_pro.fig');
        
        PRO.Ncams = Ncams;
        PRO.Nruns = Nruns;
        PRO.Xgp = Xgp;
        PRO.Xip = Xip;
        PRO.fps = FPSreq;
        PRO.err.COA_GP = err.COA_GP;
        PRO.err.COA_IP = err.COA_IP;
        PRO.err.CAMGP = err.CAMGP;
        PRO.err.CAMIP = err.CAMIP;        
        save figs/TrackErrIP_cmp_processing.mat PRO;
        
    end
end