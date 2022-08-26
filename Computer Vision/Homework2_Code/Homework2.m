%Ideal conditions for Ransac: 75000 thresh, 30 inliers, 1.25 distance
%Ideal conditions for Hough: 50000 thresh, 1 ba, 1 br

function main = main(image,threshold,mode,inliers,distance,br,bt)
%Default Values
arguments
    image string = "road.png";
    threshold string = "50000";
    mode string = "hough";
    inliers string = "30";
    distance string = "1.25";
    br string = "1";
    bt string = "1";
end
threshold = str2double(threshold);
inliers = str2double(inliers);
distance = str2double(distance);
br = str2double(br);
bt = str2double(bt);

%Read Image
image = imread(image);
hess = hessian(image);
nm=non_maxsuppression(hess,threshold);
if(mode == "nm")
    imshow(nm)
end
if(mode == "ransac" || mode == "hough")
    imshow(image)
end
hold on;
%RANSAC
if(mode == "ransac")
    ransacpoints = ransac(getpoints(nm),inliers,distance);
    % Plot Ransac
    line([ransacpoints(1,1) ransacpoints(1,3)] , [ransacpoints(1,2) ransacpoints(1,4)]);
    line([ransacpoints(2,1) ransacpoints(2,3)] , [ransacpoints(2,2) ransacpoints(2,4)]);
    line([ransacpoints(3,1) ransacpoints(3,3)] , [ransacpoints(3,2) ransacpoints(3,4)]);
    line([ransacpoints(4,1) ransacpoints(4,3)] , [ransacpoints(4,2) ransacpoints(4,4)]);
end
%HOUGH
if(mode == "hough")
    points = getpoints(nm);
    houghplot = hough(points,nm,br,bt);
    % Plot Hough
    line([houghplot(1,1) houghplot(2,1)] , [houghplot(1,2) houghplot(2,2)]);
    line([houghplot(3,1) houghplot(4,1)] , [houghplot(3,2) houghplot(4,2)]);
    line([houghplot(5,1) houghplot(6,1)] , [houghplot(5,2) houghplot(6,2)]);
    line([houghplot(7,1) houghplot(8,1)] , [houghplot(7,2) houghplot(8,2)]);
end
    



end
%%Part 1%%
%Code from first Homework%

%Pads Matrix
function padded_array = pad(image,sigma)
    %original rows, original colums
    [or,oc] = size(image);
    new_sigma = 5*sigma;
    m = zeros(or+(2*new_sigma), oc+(2*new_sigma), "double");
    m(new_sigma+1:or+new_sigma,new_sigma+1:oc+new_sigma)=image;
    
    %Top Left Corner
    for r = 1:new_sigma+1
        for c = 1:new_sigma+1
            m(r,c) = m(new_sigma+1,new_sigma+1);
       end
    end
    %Left side
    for r = new_sigma+1:or+new_sigma-1
        for c = 1:new_sigma+1
            m(r,c) = m(r,new_sigma+1);
        end
    end
     %Bottom Left Corner
     for r = or+new_sigma:or+(2*new_sigma)
        for c = 1:new_sigma+1
            m(r,c) = m(or+new_sigma,new_sigma+1);
       end
    end
     %Top
    for r = 1:new_sigma
         for c = new_sigma+1:oc+new_sigma
             m(r,c) = m(new_sigma+1,c);
         end
     end
     %Top Right Corner
     for r = 1:new_sigma+1
        for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(new_sigma+1,oc+new_sigma);
        end
     end
     %Right Side
     for r = new_sigma+1:or+new_sigma-1
         for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(r,oc+new_sigma);
         end
     end
     %Bottom Right Corner
     for r = or+new_sigma:or+(2*new_sigma)
         for c = oc+new_sigma+1:oc+(2*new_sigma)
             m(r,c) = m(or+new_sigma,oc+new_sigma);
        end
     end
     %Bottom
     for r = or+new_sigma:or+(2*new_sigma)
         for c = new_sigma+1:oc+new_sigma
             m(r,c) = m(or+new_sigma,c);
        end
     end
    padded_array=m;
    
end



%Applies any filter to an image
%Takes in a filter, image, and the extended image

%Padded version
function apply_filter = app(filter,image)
    ext_image = pad(image,1);
    [row,col] = size(image);
    [re,ce] = size(ext_image);
    [~,len] = size(filter);
    newx = re - row;
    newy = ce - col;
    image2 = zeros(row, col);
    for r = 1:row
        for c = 1:col
            newr = r +((newx)/2);
            newc = c +((newy)/2);
            piece = ext_image((newr)-((len-1)/2):(newr)+((len-1)/2),(newc)-((len-1)/2):(newc)+((len-1)/2));
            mult_matrix = filter .* piece;
            image2(r,c) = sum(mult_matrix(:));
        end
    end
    apply_filter = image2;
end


%Gets the Gaussian Filter
function get_gaussian = gauss(sigma)
   size = 6*sigma;
   filter = zeros(size-1,size-1);
   for r = 1:size-1
        for c = 1:size-1
             x = abs(r - size/2);
             y = abs(c - size/2);
             filter(r,c) = (1/(2*pi*sigma))*exp((-(x^2 + y^2))/(2*sigma^2));
             
        end
   end
   get_gaussian = filter./sum(filter,'all'); 
end

%Applies the Gaussian filter
function appgauss = appgauss(image,sigma)
    %Do the Gauss
     gaussian = gauss(sigma);
     appgauss = app(gaussian,image);
end

%Applies the Vertical Sobel Filter
function sob1 = sobel1(gaussimage)
     sobelfilt1 = [-1 0 1; -2 0 2; -1 0 1];
     sob1 = app(sobelfilt1,gaussimage);
     sob1 = double(sob1);
     
end

%Applies the Horizontal Sobel Filter
function sob2 = sobel2(gaussimage)
     sobelfilt2 = [1 2 1; 0 0 0; -1 -2 -1];
     sob2 = app(sobelfilt2,gaussimage);
     sob2 = double(sob2);
end

function hess = hessian(image)
    gaussimage = appgauss(image,1);
    sobx = sobel1(gaussimage);
    soby = sobel2(gaussimage);
    sobxx = sobel1(sobx);
    sobyy = sobel2(soby);
    sobxy = sobel2(sobx);
    hess = abs((sobxx .* sobyy) - (sobxy.^2));
end

%nonmax suppression

function non_max = non_maxsuppression(magnitude,threshold)
    [row,col] = size(magnitude);
    m = zeros(row,col, "double");
    magnitude = pad(magnitude,(1/5));
    for r = 2:row+1
         for c= 2:col+1
             if(max(magnitude(r-1:r+1,c-1:c+1), [], 'all') == magnitude(r,c))
                    m(r-1,c-1) = magnitude(r,c);
                 else
                    m(r-1,c-1) = 0;
             end
         end
    end
    for r = 1:row
        for c = 1:col
            if(abs(m(r,c))<threshold)
                m(r,c) = 0;
            end
        end
    end
    non_max = abs(m);
end

%RANSAC
function getpoints = getpoints(matrix)
    [row,col] = size(matrix);
    getpoints = [];
    for r= 1:row
        for c = 1:col
            if(matrix(r,c) ~= 0)
                getpoints = cat(1,getpoints,[c r]);
            end
        end
    end
end

%RANSAC with extreme inliers
function ransac = ransac(points,inliers,distance)
    iteration = 0;
    ransac = [];
    while(iteration < 4)
        rowlist = [];
        max = [0 0];
        min = [1000 1000];
        [row,~] = size(points);
        one=points(randi(row),1:2);
        two=points(randi(row),1:2);
        count = 0;
        while(one == two)
            one=points(randi(row),1:2);
        end
        for r=1:row
            num = abs(((two(1) - one(1)) * (one(2) - points(r,2))) - ((one(1) - points(r,1)) * (two(2) - one(2))));
            den = sqrt(((two(1) - one(1))^2) + ((two(2) - one(2))^2));
            dist = num/(den);
            if(dist <= distance)
                rowlist = cat(1,rowlist,r);
                count = count + 1;
                if(points(r,1) < min(1))
                    min = points(r,1:2);
                end
                if(points(r,1) > max(1))
                    max = points(r,1:2);
                end
            end
        end
        if(count >= inliers)
            ransac = cat(1,ransac,[min max]);
            iteration = iteration + 1;
            [f,~] = size(rowlist);
            for k = 1:f
                plot(points(rowlist(k),1), points(rowlist(k),2), '-s', 'MarkerSize', 3, 'MarkerEdgeColor','red','MarkerFaceColor',[1 .6 .6]);
            end
            points(rowlist,:) = [];
        end
    end
end



%Do hough transform
function houghpoints = hough(points,nm,br,bt)
    houghlines = [];
    [row,col] = size(nm);
    [len,~] = size(points);
    %Overestimate Accumulator
    romax = 2*(row+col) + 1;
    acc = zeros(ceil(180/bt),ceil(romax/br));
    for i = 1 : len
        for theta = 1:180
            ro = points(i,1)*cosd(theta) + points(i,2)*sind(theta);
            ro = ro + row + col + 1;
            acc(ceil(theta/bt),ceil(ro/br)) = acc(ceil(theta/bt),ceil(ro/br)) + 1;
        end
    end
    for j = 1:4
        [theta, ro] = find(ismember(acc, max(acc(:))));
        houghlines = cat(1,houghlines,[theta ro]);
        acc(theta,ro) = 0;
    end
    max1 = [0 0];
    max2 = [0 0];
    max3 = [0 0];
    max4 = [0 0];
    min1 = [100000 100000];
    min2 = [100000 100000];
    min3 = [100000 100000];
    min4 = [100000 100000];
    
    for i = 1 : len
        for theta = 1:180
            ro = points(i,1)*cosd(theta) + points(i,2)*sind(theta);
            ro = ro + row + col + 1;
            ro = ceil(ro/br);
            temptheta=ceil(theta/bt);
            if(temptheta == houghlines(1,1) && ro == houghlines(1,2))
                if(points(i,1) > max1(1))
                    max1 = points(i,1:2);
                end
                if(points(i,1) < min1(1))
                    min1 = points(i,1:2);
                end
               plot(points(i,1), points(i,2), '-s', 'MarkerSize', 3, 'MarkerEdgeColor','red','MarkerFaceColor',[1 .6 .6]); 
            end
            if(temptheta == houghlines(2,1) && ro == houghlines(2,2))
                if(points(i,1) > max2(1))
                    max2 = points(i,1:2);
                end
                if(points(i,1) < min2(1))
                    min2 = points(i,1:2);
                end
               plot(points(i,1), points(i,2), '-s', 'MarkerSize', 3, 'MarkerEdgeColor','red','MarkerFaceColor',[1 .6 .6]); 
            end
            if(temptheta == houghlines(3,1) && ro == houghlines(3,2))
                if(points(i,1) > max3(1))
                    max3 = points(i,1:2);
                end
                if(points(i,1) < min3(1))
                    min3 = points(i,1:2);
                end
               plot(points(i,1), points(i,2), '-s', 'MarkerSize', 3, 'MarkerEdgeColor','red','MarkerFaceColor',[1 .6 .6]); 
            end
            if(temptheta == houghlines(4,1) && ro == houghlines(4,2))
                if(points(i,1) > max4(1))
                    max4 = points(i,1:2);
                end
                if(points(i,1) < min4(1))
                    min4 = points(i,1:2);
                end
               plot(points(i,1), points(i,2), '-s', 'MarkerSize', 3, 'MarkerEdgeColor','red','MarkerFaceColor',[1 .6 .6]); 
            end
        end
        
       
    end
    houghpoints = [];
       houghpoints = cat(1,houghpoints,max1);
       houghpoints = cat(1,houghpoints,min1);
       houghpoints = cat(1,houghpoints,max2);
       houghpoints = cat(1,houghpoints,min2);
       houghpoints = cat(1,houghpoints,max3);
       houghpoints = cat(1,houghpoints,min3);
       houghpoints = cat(1,houghpoints,max4);
       houghpoints = cat(1,houghpoints,min4);


end



 
 
 
 